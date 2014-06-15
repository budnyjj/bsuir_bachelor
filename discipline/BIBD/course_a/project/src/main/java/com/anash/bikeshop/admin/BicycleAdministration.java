package com.anash.bikeshop.admin;

import com.anash.bikeshop.entity.Bicycle;
import org.lightadmin.api.config.AdministrationConfiguration;
import org.lightadmin.api.config.annotation.Administration;

@Administration(Bicycle.class)
public class BicycleAdministration extends AdministrationConfiguration<Bicycle> {
}
