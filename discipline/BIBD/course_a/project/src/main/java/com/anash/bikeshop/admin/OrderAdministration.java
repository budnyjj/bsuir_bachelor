package com.anash.bikeshop.admin;

import com.anash.bikeshop.entity.Order;
import org.lightadmin.api.config.AdministrationConfiguration;
import org.lightadmin.api.config.annotation.Administration;

@Administration(Order.class)
public class OrderAdministration extends AdministrationConfiguration<Order> {

    /*
    public FieldSetConfigurationUnit configurationUnit (
            final PersistentFieldSetConfigurationUnitBuilder unitBuilder) {


        return unitBuilder
                .field("orderStatus").caption("Order status")
                .enumeration(
                        element(1, "PROCESSING"),
                        element(2, "COMPLETED"),
                        element(3, "CANCELED"))
                .build();
    }
    */

}
