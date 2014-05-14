package com.anash.abstrfactory.abstrfactory;

import com.anash.abstrfactory.abstrproduct.AAddress;
import com.anash.abstrfactory.abstrproduct.APhoneNumber;

public interface IAddressFactory {
    public AAddress createAddress();
    public APhoneNumber createPhoneNumber();
}
