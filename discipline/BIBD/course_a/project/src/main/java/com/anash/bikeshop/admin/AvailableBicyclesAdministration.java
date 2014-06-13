package com.anash.bikeshop.admin;

import com.anash.bikeshop.entity.AvailableBicycles;
import org.lightadmin.api.config.AdministrationConfiguration;
import org.lightadmin.api.config.annotation.Administration;

@Administration(AvailableBicycles.class)
public class AvailableBicyclesAdministration extends
        AdministrationConfiguration<AvailableBicycles> {

}
