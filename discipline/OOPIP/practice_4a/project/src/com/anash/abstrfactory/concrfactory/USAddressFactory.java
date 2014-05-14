package com.anash.abstrfactory.concrfactory;

import com.anash.abstrfactory.abstrfactory.IAddressFactory;
import com.anash.abstrfactory.abstrproduct.AAddress;
import com.anash.abstrfactory.abstrproduct.APhoneNumber;
import com.anash.abstrfactory.concrproduct.usproduct.USAddress;
import com.anash.abstrfactory.concrproduct.usproduct.USPhoneNumber;

public class USAddressFactory implements IAddressFactory {

    @Override
    public AAddress createAddress() {
        return new USAddress();
    }

    @Override
    public APhoneNumber createPhoneNumber() {
        return new USPhoneNumber();
    }
}
