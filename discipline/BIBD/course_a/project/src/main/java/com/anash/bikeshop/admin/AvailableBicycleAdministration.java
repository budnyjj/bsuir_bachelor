package com.anash.bikeshop.admin;

import com.anash.bikeshop.entity.AvailableBicycle;
import org.lightadmin.api.config.AdministrationConfiguration;
import org.lightadmin.api.config.annotation.Administration;

@Administration(AvailableBicycle.class)
public class AvailableBicycleAdministration extends
        AdministrationConfiguration<AvailableBicycle> {

}
