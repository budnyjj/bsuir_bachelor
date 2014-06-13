package com.anash.bikeshop.admin;

import com.anash.bikeshop.entity.Users;
import org.lightadmin.api.config.AdministrationConfiguration;
import org.lightadmin.api.config.annotation.Administration;

@Administration(Users.class)
public class UsersAdministration extends AdministrationConfiguration<Users> {

    /*
    @Override
    public EntityMetadataConfigurationUnit configuration (
            EntityMetadataConfigurationUnitBuilder configurationBuilder) {
        return configurationBuilder.nameField("email").build();
    }

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
    */
}
