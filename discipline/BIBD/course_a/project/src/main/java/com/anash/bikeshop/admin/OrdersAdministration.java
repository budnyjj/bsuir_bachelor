package com.anash.bikeshop.admin;

import com.anash.bikeshop.entity.Orders;
import org.lightadmin.api.config.AdministrationConfiguration;
import org.lightadmin.api.config.annotation.Administration;

@Administration(Orders.class)
public class OrdersAdministration extends AdministrationConfiguration<Orders> {
}
