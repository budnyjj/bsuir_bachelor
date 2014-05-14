package com.anash.abstrfactory.concrproduct.frenchproduct;

import com.anash.abstrfactory.abstrproduct.APhoneNumber;

public class FrenchPhoneNumber extends APhoneNumber {
    private static final String COUNTRY_CODE = "33";
    private static final int NUMBER_LENGTH = 9;

    @Override
    public String getCountryCode() {
        return COUNTRY_CODE;
    }


    @Override
    public void setPhoneNumber(String phoneNumber) {
        if (phoneNumber.length() == NUMBER_LENGTH) {
            super.setPhoneNumber(phoneNumber);
        }
    }
}
