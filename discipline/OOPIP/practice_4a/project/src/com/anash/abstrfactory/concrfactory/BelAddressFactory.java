package com.anash.abstrfactory.concrfactory;

import com.anash.abstrfactory.abstrfactory.IAddressFactory;
import com.anash.abstrfactory.abstrproduct.AAddress;
import com.anash.abstrfactory.abstrproduct.APhoneNumber;
import com.anash.abstrfactory.concrproduct.belproduct.BelAddress;
import com.anash.abstrfactory.concrproduct.belproduct.BelPhoneNumber;

public class BelAddressFactory implements IAddressFactory {

    @Override
    public AAddress createAddress() {
        return new BelAddress();
    }

    @Override
    public APhoneNumber createPhoneNumber() {
        return new BelPhoneNumber();
    }
}
