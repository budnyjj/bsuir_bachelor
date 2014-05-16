package com.anash.abstrfactory.concrfactory;

import com.anash.abstrfactory.abstrfactory.IAddressFactory;
import com.anash.abstrfactory.abstrproduct.AAddress;
import com.anash.abstrfactory.abstrproduct.APhoneNumber;
import com.anash.abstrfactory.concrproduct.frenchproduct.FrenchAddress;
import com.anash.abstrfactory.concrproduct.frenchproduct.FrenchPhoneNumber;

public class FrenchAddressFactory implements IAddressFactory {

    @Override
    public AAddress createAddress() {
        return new FrenchAddress();
    }

    @Override
    public APhoneNumber createPhoneNumber() {
        return new FrenchPhoneNumber();
    }
}
