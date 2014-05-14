package com.anash.abstrfactory.concrproduct.belproduct;

import com.anash.abstrfactory.abstrproduct.AAddress;

public class BelAddress extends AAddress {
    private static final String COUNTRY = "REPUBLIC OF BELARUS";

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