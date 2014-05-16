package com.anash.abstrfactory.abstrproduct;

public abstract class APhoneNumber {
    private String phoneNumber;
    public abstract String getCountryCode();

    public String getPhoneNumber() {
        return phoneNumber;
    }

    public void setPhoneNumber(String phoneNumber) {
        try {
            Long.parseLong(phoneNumber);
            this.phoneNumber = phoneNumber;
        } catch (NumberFormatException e) {
            e.printStackTrace();
        }
    }
}