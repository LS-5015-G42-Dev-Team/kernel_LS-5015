/* Copyright (c) 2012-2014, The Linux Foundation. All rights reserved.
 * Copyright (c) 2015 Francisco Franco
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/msm_tsens.h>
#include <linux/workqueue.h>
#include <linux/cpu.h>
#include <linux/cpufreq.h>
#include <linux/msm_tsens.h>
#include <linux/msm_thermal.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/hrtimer.h>

unsigned int temp_threshold = 65;
module_param(temp_threshold, int, 0644);

// Core Control sysFS Toggle.
bool core_control = true;
static struct kobject *cc_kobj;

uint32_t Throttle_Freq = 800000;

static struct thermal_info {
	uint32_t cpuinfo_max_freq;
	uint32_t limited_max_freq;
	unsigned int safe_diff;
	bool throttling;
	bool pending_change;
	const int min_interval_us;
	u64 limit_cpu_time;
} info = {
	.cpuinfo_max_freq = UINT_MAX,
	.limited_max_freq = UINT_MAX,
	.safe_diff = 5,
	.throttling = false,
	.pending_change = false,
	/* 1 second */
	.min_interval_us = 1000000,
};

struct msm_thermal_data msm_thermal_info;

static struct delayed_work check_temp_work;

static int msm_thermal_cpufreq_callback(struct notifier_block *nfb,
		unsigned long event, void *data)
{
	struct cpufreq_policy *policy = data;

	if (event != CPUFREQ_ADJUST && !info.pending_change)
		return 0;

	cpufreq_verify_within_limits(policy, policy->cpuinfo.min_freq,
		info.limited_max_freq);

	return 0;
}

static struct notifier_block msm_thermal_cpufreq_notifier = {
	.notifier_call = msm_thermal_cpufreq_callback,
};

static void limit_cpu_freqs(uint32_t max_freq)
{
	unsigned int cpu;

	if (info.limited_max_freq == max_freq)
		return;

	info.limited_max_freq = max_freq;
	info.pending_change = true;
	info.limit_cpu_time = ktime_to_us(ktime_get());

	get_online_cpus();
	for_each_online_cpu(cpu) {
		cpufreq_update_policy(cpu);
		pr_info("%s: Setting cpu%d max frequency to %d\n",
				KBUILD_MODNAME, cpu, info.limited_max_freq);
	}
	put_online_cpus();

	info.pending_change = false;
}

static void __ref check_temp(struct work_struct *work)
{
	struct tsens_device tsens_dev;
	uint32_t freq = 0;
	long temp = 0;
	u64 now;

	tsens_dev.sensor_num = msm_thermal_info.sensor_id;
	tsens_get_temp(&tsens_dev, &temp);

	if (info.throttling)
	{
		if (temp < (temp_threshold - info.safe_diff))
		{
			now = ktime_to_us(ktime_get());

			if (now < (info.limit_cpu_time + info.min_interval_us))
				goto reschedule;

			limit_cpu_freqs(info.cpuinfo_max_freq);
			info.throttling = false;
			goto reschedule;
		}
	}

	if (temp >= temp_threshold)
	   freq = Throttle_Freq;

	if (freq)
	{
		limit_cpu_freqs(freq);

		if (!info.throttling)
			info.throttling = true;
	}

	// Begin HotPlug Mechanism for Shoaib's Core Control.
	if (core_control)
	{
	   if (temp >= 81)
	   {
	      // Enable Core 0 (big).
	      if (!cpu_online(0))
		 cpu_up(0);

	      // Disable Cores (big).
	      if (cpu_online(3))
	      	 cpu_down(3);
	      if (cpu_online(2))
	         cpu_down(2);
	      if (cpu_online(1))
	         cpu_down(1);

	      // Disable Cores (LITTLE).
	      if (cpu_online(7))
	         cpu_down(7);
	      if (cpu_online(6))
	         cpu_down(6); 
	   }
	   else if (temp >= 60 && temp <= 80)
	   {
		   // Enable Cores (LITTLE).
		   if (!cpu_online(6))
		      cpu_up(6);
	           if (!cpu_online(7))
	 	      cpu_up(7);

		   // Disable Cores (big).
	           if (cpu_online(3))
	      	      cpu_down(3);
	           if (cpu_online(2))
	              cpu_down(2);
		   if (cpu_online(1))
	              cpu_down(1);
	   }
	   else if (temp >= 49 && temp <= 59)
	   {
		   // Enable Cores (big).
	           if (!cpu_online(0))
	              cpu_up(0);
	           if (!cpu_online(1))
	              cpu_up(1);
	 
		   // Disable Cores (big).         
	           if (cpu_online(3))
	              cpu_down(3);
	           if (cpu_online(2))
	              cpu_down(2);
	   }
	   else if (temp == 45)
	   {
	           int cpu;
	           for_each_possible_cpu(cpu)
	               if (!cpu_online(cpu))
		          cpu_up(cpu);
	   }
	}
	// End HotPlug Mechanism for Shoaib's Core Control.

reschedule:
	schedule_delayed_work_on(0, &check_temp_work, msecs_to_jiffies(250));
}

// Begin sysFS for Shoaib's Core Control.
static ssize_t show_cc_enabled (struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return snprintf (buf, PAGE_SIZE, "%d\n", core_control);
}

static ssize_t __ref store_cc_enabled (struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	int ret = 0;
	int val = 0;

	ret = kstrtoint (buf, 10, &val);
	if (ret)
	{
	   pr_err("Invalid input %s. err:%d\n", buf, ret);
	   goto done_store_cc;
	}

	if (core_control == !!val)
	   goto done_store_cc;

	core_control = !!val;

	if (!core_control)
	{
	   int cpu;
	   /* Wake-Up All the Sibling Cores */
	   for_each_possible_cpu(cpu)
	       if (!cpu_online(cpu))
		  cpu_up(cpu);
	}

done_store_cc:
	return count;
}

static __refdata struct kobj_attribute cc_enabled_attr = 
__ATTR(core_control, 0644, show_cc_enabled, store_cc_enabled);

static __refdata struct attribute *cc_attrs[] = {
	&cc_enabled_attr.attr,
	NULL,
};

static __refdata struct attribute_group cc_attr_group = {
	.attrs = cc_attrs,
};

static __init int msm_thermal_add_cc_nodes(void)
{
	struct kobject *module_kobj = NULL;
	int ret = 0;

	module_kobj = kset_find_obj(module_kset, KBUILD_MODNAME);
	if (!module_kobj) 
	{
	   pr_err("cannot find kobject\n");
	   ret = -ENOENT;
	   goto done_cc_nodes;
	}

	cc_kobj = kobject_create_and_add("core_control", module_kobj);
	if (!cc_kobj) 
	{
	   pr_err("cannot create core control kobj\n");
	   ret = -ENOMEM;
	   goto done_cc_nodes;
	}

	ret = sysfs_create_group(cc_kobj, &cc_attr_group);
	if (ret) 
	{
	   pr_err("cannot create sysfs group. err:%d\n", ret);
	   goto done_cc_nodes;
	}

	return 0;

done_cc_nodes:
	if (cc_kobj)
	   kobject_del(cc_kobj);
	return ret;
}
// End sysFS for Shoaib's Core Control.

static int msm_thermal_dev_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct device_node *node = pdev->dev.of_node;
	struct msm_thermal_data data;

	memset(&data, 0, sizeof(struct msm_thermal_data));

	ret = of_property_read_u32(node, "qcom,sensor-id", &data.sensor_id);
	if (ret)
		return ret;

	WARN_ON(data.sensor_id >= TSENS_MAX_SENSORS);

        memcpy(&msm_thermal_info, &data, sizeof(struct msm_thermal_data));

        INIT_DELAYED_WORK(&check_temp_work, check_temp);
        schedule_delayed_work_on(0, &check_temp_work, 10 * HZ);

	cpufreq_register_notifier(&msm_thermal_cpufreq_notifier,
			CPUFREQ_POLICY_NOTIFIER);

	return ret;
}

static int msm_thermal_dev_remove(struct platform_device *pdev)
{
	cpufreq_unregister_notifier(&msm_thermal_cpufreq_notifier,
                        CPUFREQ_POLICY_NOTIFIER);
	return 0;
}

static struct of_device_id msm_thermal_match_table[] = {
	{.compatible = "qcom,msm-thermal"},
	{},
};

static struct platform_driver msm_thermal_device_driver = {
	.probe = msm_thermal_dev_probe,
	.remove = msm_thermal_dev_remove,
	.driver = {
		.name = "msm-thermal",
		.owner = THIS_MODULE,
		.of_match_table = msm_thermal_match_table,
	},
};

int __init  msm_thermal_device_init(void)
{
	// Initialize Shoaib's Core Control Driver only for Octa-Core SoCs.
	if (num_possible_cpus() == 8)
	   msm_thermal_add_cc_nodes();

	return platform_driver_register(&msm_thermal_device_driver);
}

void __exit msm_thermal_device_exit(void)
{
	platform_driver_unregister(&msm_thermal_device_driver);
}

late_initcall(msm_thermal_device_init);
module_exit(msm_thermal_device_exit);
