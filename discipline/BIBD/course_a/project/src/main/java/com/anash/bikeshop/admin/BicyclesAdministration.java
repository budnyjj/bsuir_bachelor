package com.anash.bikeshop.admin;

import com.anash.bikeshop.entity.Bicycles;
import org.lightadmin.api.config.AdministrationConfiguration;
import org.lightadmin.api.config.annotation.Administration;

@Administration(Bicycles.class)
public class BicyclesAdministration extends AdministrationConfiguration<Bicycles> {
}
