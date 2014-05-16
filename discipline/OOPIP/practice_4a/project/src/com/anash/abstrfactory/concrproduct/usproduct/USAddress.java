package com.anash.abstrfactory.concrproduct.usproduct;

import com.anash.abstrfactory.abstrproduct.AAddress;

public class USAddress extends AAddress {
    private static final String COUNTRY = "UNITED STATES";
    private static final String COMMA = ",";

    @Override
    public String getCountry() {
        return COUNTRY;
    }

    public String getFullAddress() {
        return getStreet() + EOL_STRING + getCity()+ COMMA + SPACE +
                getPostalCode() + EOL_STRING + COUNTRY + EOL_STRING;
    }
}
