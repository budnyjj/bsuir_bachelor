package com.anash.bikeshop.admin;

import com.anash.bikeshop.entity.OrderArchive;
import org.lightadmin.api.config.AdministrationConfiguration;
import org.lightadmin.api.config.annotation.Administration;

@Administration(OrderArchive.class)
public class OrderArchiveAdministration extends
        AdministrationConfiguration<OrderArchive> {
}
