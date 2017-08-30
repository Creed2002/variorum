#include <stdio.h>

#include <Haswell_3F.h>
#include <clocks_features.h>
#include <config_architecture.h>
#include <counters_features.h>
#include <power_features.h>
#include <thermal_features.h>

static struct haswell_3f_offsets msrs =
{
    .msr_platform_info            = 0xCE,
    .ia32_time_stamp_counter      = 0x10,
    .ia32_perf_ctl                = 0x199,
    .ia32_perf_status             = 0x198,
    .ia32_therm_interrupt         = 0x19B,
    .ia32_therm_status            = 0x19C,
    .ia32_misc_enable             = 0x1A0,
    .msr_temperature_target       = 0x1A2,
    .msr_turbo_ratio_limit        = 0x1AD,
    .msr_turbo_ratio_limit1       = 0x1AE,
    .ia32_package_therm_status    = 0x1B1,
    .ia32_package_therm_interrupt = 0x1B2,
    .ia32_fixed_counters[0]       = 0x309,
    .ia32_fixed_counters[1]       = 0x30A,
    .ia32_fixed_counters[2]       = 0x30B,
    .ia32_fixed_ctr_ctrl          = 0x38D,
    .ia32_perf_global_status      = 0x38E,
    .ia32_perf_global_ctrl        = 0x38F,
    .ia32_perf_global_ovf_ctrl    = 0x390,
    .msr_rapl_power_unit          = 0x606,
    .msr_pkg_power_limit          = 0x610,
    .msr_pkg_energy_status        = 0x611,
    .msr_pkg_perf_status          = 0x613,
    .msr_pkg_power_info           = 0x614,
    .msr_dram_power_limit         = 0x618,
    .msr_dram_energy_status       = 0x619,
    .msr_dram_perf_status         = 0x61B,
    .msr_turbo_activation_ratio   = 0x64C,
    .ia32_mperf                   = 0xE7,
    .ia32_aperf                   = 0xE8,
    .ia32_perfmon_counters[0]     = 0xC1,
    .ia32_perfmon_counters[1]     = 0xC2,
    .ia32_perfmon_counters[2]     = 0xC3,
    .ia32_perfmon_counters[3]     = 0xC4,
    .ia32_perfmon_counters[4]     = 0xC5,
    .ia32_perfmon_counters[5]     = 0xC6,
    .ia32_perfmon_counters[6]     = 0xC7,
    .ia32_perfmon_counters[7]     = 0xC8,
    .ia32_perfevtsel_counters[0]  = 0x186,
    .ia32_perfevtsel_counters[1]  = 0x187,
    .ia32_perfevtsel_counters[2]  = 0x188,
    .ia32_perfevtsel_counters[3]  = 0x189,
    .ia32_perfevtsel_counters[4]  = 0x18A,
    .ia32_perfevtsel_counters[5]  = 0x18B,
    .ia32_perfevtsel_counters[6]  = 0x18C,
    .ia32_perfevtsel_counters[7]  = 0x18D,
};

int fm_06_3f_get_power_limits(int long_ver)
{
    int socket;
    int nsockets, ncores, nthreads;
    variorum_set_topology(&nsockets, &ncores, &nthreads);

    printf("Running %s\n", __FUNCTION__);

    for (socket = 0; socket < nsockets; socket++)
    {
        if (long_ver == 0)
        {
            dump_package_power_limit(stdout, msrs.msr_pkg_power_limit, msrs.msr_rapl_power_unit, socket);
        }
        else if (long_ver == 1)
        {
            print_package_power_limit(stdout, msrs.msr_pkg_power_limit, msrs.msr_rapl_power_unit, socket);
        }
    }

    for (socket = 0; socket < nsockets; socket++)
    {
        if (long_ver == 0)
        {
            dump_dram_power_limit(stdout, msrs.msr_dram_power_limit, msrs.msr_rapl_power_unit, socket);
        }
        else if (long_ver == 1)
        {
            print_dram_power_limit(stdout, msrs.msr_dram_power_limit, msrs.msr_rapl_power_unit, socket);
        }
    }

    for (socket = 0; socket < nsockets; socket++)
    {
        if (long_ver == 0)
        {
            dump_package_power_info(stdout, msrs.msr_pkg_power_info, socket);
        }
        else if (long_ver == 1)
        {
            print_package_power_info(stdout, msrs.msr_pkg_power_info, socket);
        }
    }

    if (long_ver == 0)
    {
        dump_rapl_power_unit(stdout, msrs.msr_rapl_power_unit);
    }
    else if (long_ver == 1)
    {
        print_rapl_power_unit(stdout, msrs.msr_rapl_power_unit);
    }

    return 0;
}

int fm_06_3f_set_power_limits(int package_power_limit)
{
    int socket;
    int nsockets, ncores, nthreads;
    variorum_set_topology(&nsockets, &ncores, &nthreads);

    printf("Running %s\n", __FUNCTION__);

    for (socket = 0; socket < nsockets; socket++)
    {
        set_package_power_limit(socket, package_power_limit, msrs.msr_pkg_power_limit, msrs.msr_rapl_power_unit);
    }
    return 0;
}

int fm_06_3f_get_features(void)
{
    printf("Running %s\n", __FUNCTION__);

    fprintf(stdout, "ia32_time_stamp_counter      = 0x10\n");
    fprintf(stdout, "ia32_perf_ctl                = 0x199\n");
    fprintf(stdout, "ia32_therm_interrupt         = 0x19B\n");
    fprintf(stdout, "ia32_therm_status            = 0x19C\n");
    fprintf(stdout, "ia32_misc_enable             = 0x1A0\n");
    fprintf(stdout, "msr_temperature_target       = 0x1A2\n");
    fprintf(stdout, "msr_turbo_ratio_limit        = 0x1AD\n");
    fprintf(stdout, "msr_turbo_ratio_limit1       = 0x1AE\n");
    fprintf(stdout, "ia32_package_therm_status    = 0x1B1\n");
    fprintf(stdout, "ia32_package_therm_interrupt = 0x1B2\n");
    fprintf(stdout, "ia32_fixed_ctr0              = 0x309\n");
    fprintf(stdout, "ia32_fixed_ctr1              = 0x30A\n");
    fprintf(stdout, "ia32_fixed_ctr2              = 0x30B\n");
    fprintf(stdout, "ia32_fixed_ctr_ctrl          = 0x38D\n");
    fprintf(stdout, "ia32_perf_global_status      = 0x38E\n");
    fprintf(stdout, "ia32_perf_global_ctrl        = 0x38F\n");
    fprintf(stdout, "ia32_perf_global_ovf_ctrl    = 0x390\n");
    fprintf(stdout, "msr_rapl_power_unit          = 0x606\n");
    fprintf(stdout, "msr_pkg_power_limit          = 0x610\n");
    fprintf(stdout, "msr_pkg_energy_status        = 0x611\n");
    fprintf(stdout, "msr_pkg_perf_status          = 0x613\n");
    fprintf(stdout, "msr_pkg_power_info           = 0x614\n");
    fprintf(stdout, "msr_dram_power_limit         = 0x618\n");
    fprintf(stdout, "msr_dram_energy_status       = 0x619\n");
    fprintf(stdout, "msr_dram_perf_status         = 0x61B\n");
    fprintf(stdout, "msr_turbo_activation_ratio   = 0x64C\n");
    fprintf(stdout, "ia32_mperf                   = 0xE7\n");
    fprintf(stdout, "ia32_aperf                   = 0xE8\n");
    return 0;
}

int fm_06_3f_get_thermals(int long_ver)
{
    printf("Running %s\n", __FUNCTION__);

    if (long_ver == 0)
    {
        dump_therm_temp_reading(stdout, msrs.ia32_therm_status, msrs.ia32_package_therm_status, msrs.msr_temperature_target);
    }
    else if (long_ver == 1)
    {
        print_therm_temp_reading(stdout, msrs.ia32_therm_status, msrs.ia32_package_therm_status, msrs.msr_temperature_target);
    }
    return 0;
}

int fm_06_3f_get_counters(int long_ver)
{
    printf("Running %s\n", __FUNCTION__);

    if (long_ver == 0)
    {
        dump_all_counter_data(stdout, msrs.ia32_fixed_counters, msrs.ia32_perf_global_ctrl, msrs.ia32_fixed_ctr_ctrl, msrs.ia32_perfevtsel_counters, msrs.ia32_perfmon_counters, msrs.msrs_pcu_pmon_evtsel, msrs.ia32_perfevtsel_counters);
    }
    else if (long_ver == 1)
    {
        print_all_counter_data(stdout, msrs.ia32_fixed_counters, msrs.ia32_perf_global_ctrl, msrs.ia32_fixed_ctr_ctrl, msrs.ia32_perfevtsel_counters, msrs.ia32_perfmon_counters, msrs.msrs_pcu_pmon_evtsel, msrs.ia32_perfevtsel_counters);
    }
    return 0;
}

int fm_06_3f_get_clocks(int long_ver)
{
    printf("Running %s\n", __FUNCTION__);

    if (long_ver == 0)
    {
        dump_clocks_data_core(stdout, msrs.ia32_aperf, msrs.ia32_mperf, msrs.ia32_time_stamp_counter, msrs.ia32_perf_status, msrs.msr_platform_info);
    }
    else if (long_ver == 1)
    {
        print_clocks_data_core(stdout, msrs.ia32_aperf, msrs.ia32_mperf, msrs.ia32_time_stamp_counter, msrs.ia32_perf_status, msrs.msr_platform_info);
    }
    return 0;
}

int fm_06_3f_get_power(int long_ver)
{
    printf("Running %s\n", __FUNCTION__);

    if (long_ver == 0)
    {
        dump_power_data(stdout, msrs.msr_pkg_power_limit, msrs.msr_rapl_power_unit, msrs.msr_pkg_energy_status, msrs.msr_dram_energy_status);
    }
    else if (long_ver == 1)
    {
        print_power_data(stdout, msrs.msr_pkg_power_limit, msrs.msr_rapl_power_unit, msrs.msr_pkg_energy_status, msrs.msr_dram_energy_status);
    }
    return 0;
}