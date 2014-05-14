package com.anash.abstrfactory.abstrproduct;

public abstract class AAddress {
    private String street;
    private String city;
    private String region;
    private String postalCode;

    public static final String EOL_STRING =
            System.getProperty("line.separator");
    public static final String SPACE = " ";

    public abstract String getCountry();

    public String getFullAddress() {
        return this.street + EOL_STRING + city + SPACE +
                postalCode + EOL_STRING;
    }

    public String getStreet() {
        return street;
    }

    public void setStreet(String newStreet) {
        street = newStreet;
    }

    public String getCity() {
        return city;
    }

    public void setCity(String newCity) {
        city = newCity;
    }

    public String getRegion() {
        return region;
    }

    public void setRegion(String newRegion) {
        region = newRegion;
    }

    public String getPostalCode() {
        return postalCode;
    }

    public void setPostalCode(String newPostalCode) {
        postalCode = newPostalCode;
    }
}