package com.anash.abstrfactory.runner;

import com.anash.abstrfactory.abstrfactory.IAddressFactory;
import com.anash.abstrfactory.abstrproduct.AAddress;
import com.anash.abstrfactory.abstrproduct.APhoneNumber;
import com.anash.abstrfactory.concrfactory.BelAddressFactory;
import com.anash.abstrfactory.concrfactory.FrenchAddressFactory;
import com.anash.abstrfactory.concrfactory.USAddressFactory;

public class Run {
    public static void main(String[] args) {
        IAddressFactory factory;
        AAddress address;
        APhoneNumber phoneNumber;

        System.out.println("=== US Factory usage ===");
        factory = new USAddressFactory();
        address = factory.createAddress();
        phoneNumber = factory.createPhoneNumber();

        address.setCity("New York");
        address.setRegion("New York");
        address.setPostalCode("08400");
        address.setStreet("Brain str.");
        phoneNumber.setPhoneNumber("8735171725");
        System.out.println(address.getFullAddress());
        System.out.println(phoneNumber.getPhoneNumber());

        System.out.println("=== Bel Factory usage ===");
        factory = new BelAddressFactory();
        address = factory.createAddress();
        phoneNumber = factory.createPhoneNumber();
        address.setCity("Minsk");
        address.setStreet("M. Bogdanovicha");
        address.setPostalCode("220100");
        phoneNumber.setPhoneNumber("80291717253");
        System.out.println(address.getFullAddress());
        System.out.println(phoneNumber.getPhoneNumber());

        System.out.println("=== French Factory usage ===");
        factory = new FrenchAddressFactory();
        address = factory.createAddress();
        phoneNumber = factory.createPhoneNumber();
        address.setCity("Paris");
        address.setStreet("Eifel str");
        address.setRegion("Paris");
        address.setPostalCode("01234");
        phoneNumber.setPhoneNumber("824123451");
        System.out.println(address.getFullAddress());
        System.out.println(phoneNumber.getPhoneNumber());
    }
}
