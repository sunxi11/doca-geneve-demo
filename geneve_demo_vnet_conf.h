/*
 * Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES, ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of NVIDIA CORPORATION &
 * AFFILIATES (the "Company") and all right, title, and interest in and to the
 * software product, including all associated intellectual property rights, are
 * and shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 *
 */
#pragma once

#include <geneve_demo.h>

// Describes a VF, including its index relateive to the parent PF,
// and its MAC address.
// Not to be confused with the corresponding port representor.
struct vnic_t
{
    uint16_t vf_index;
    const char *name;
    struct rte_ether_addr mac_addr;
    struct doca_pci_bdf pci;
    ipv6_addr_t ip;
    // The same VNET ID is applied to all outgoing flows on this interface
    uint32_t vnet_id_out;
};

// Describes a PF, including VFs owned by it.
// All flows are created on this device.
struct nic_t
{
    const char *name;
    struct rte_ether_addr mac_addr;
    struct doca_pci_bdf pci;
    ipv6_addr_t ip;
    uint16_t num_vnics;
    struct vnic_t *vnics;
};

// Describes a collection of physical and virtual NICs.
struct vnet_host_t
{
    const char *name;
    uint16_t num_nics;
    struct nic_t *nics;
};

struct route_t
{
    const char *hostname[2];
    const char *vnic_name[2];
};

// A configuration which describes all the physical hosts on
// a physical network, and all the virtual networks which
// span the physical hosts.
struct vnet_config_t
{
    uint16_t num_hosts;
    struct vnet_host_t *hosts;
    uint16_t num_routes;
    struct route_t *routes;
};

int load_vnet_config(const char *config_json_path, struct vnet_config_t *config);

