package com.anash.abstrfactory.concrproduct.frenchproduct;

import com.anash.abstrfactory.abstrproduct.AAddress;

public class FrenchAddress extends AAddress {
    private static final String COUNTRY = "FRANCE";

    @Override
    public String getCountry() {
        return COUNTRY;
    }

    @Override
    public String getFullAddress() {
        return getStreet() + EOL_STRING + getPostalCode() + SPACE +
                getCity() + EOL_STRING + COUNTRY + EOL_STRING;
    }
}
