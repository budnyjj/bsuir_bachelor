package com.anash.abstrfactory.concrproduct.usproduct;

import com.anash.abstrfactory.abstrproduct.APhoneNumber;

public class USPhoneNumber extends APhoneNumber {
    private static final String COUNTRY_CODE = "01";
    private static final int NUMBER_LENGTH = 10;

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
