package com.anash.bikeshop.admin;

import com.anash.bikeshop.entity.OrdersArchive;
import org.lightadmin.api.config.AdministrationConfiguration;
import org.lightadmin.api.config.annotation.Administration;

@Administration(OrdersArchive.class)
public class OrdersArchiveAdministration extends
        AdministrationConfiguration<OrdersArchive> {
}
