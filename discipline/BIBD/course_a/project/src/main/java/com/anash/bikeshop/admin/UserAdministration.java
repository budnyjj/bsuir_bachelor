package com.anash.bikeshop.admin;

import com.anash.bikeshop.entity.User;
import org.lightadmin.api.config.AdministrationConfiguration;
import org.lightadmin.api.config.annotation.Administration;
import org.lightadmin.api.config.builder.FieldSetConfigurationUnitBuilder;
import org.lightadmin.api.config.builder.ScreenContextConfigurationUnitBuilder;
import org.lightadmin.api.config.unit.FieldSetConfigurationUnit;
import org.lightadmin.api.config.unit.ScreenContextConfigurationUnit;

@Administration(User.class)
public class UserAdministration extends AdministrationConfiguration<User> {

    @Override
    public ScreenContextConfigurationUnit screenContext (
            ScreenContextConfigurationUnitBuilder screenContextBuilder) {
        return screenContextBuilder.screenName("Users Administration").build();
    }

    @Override
    public FieldSetConfigurationUnit listView (
            FieldSetConfigurationUnitBuilder fragmentBuilder) {
        return fragmentBuilder.field("email").caption("E-mail").build();
    }

}
