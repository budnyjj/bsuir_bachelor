package com.anash.abstrfactory.concrproduct.belproduct;

import com.anash.abstrfactory.abstrproduct.APhoneNumber;

public class BelPhoneNumber extends APhoneNumber {
    private static final String COUNTRY_CODE = "??";
    private static final int NUMBER_LENGTH = 11;

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
