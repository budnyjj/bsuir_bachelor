package com.anash.bridge.abstraction;

import com.anash.bridge.abstraction.BaseList;

public class NumberedList extends BaseList {
    @Override
    public String get(int index) {
        return (index + 1) + ". " + super.get(index);
    }
}
