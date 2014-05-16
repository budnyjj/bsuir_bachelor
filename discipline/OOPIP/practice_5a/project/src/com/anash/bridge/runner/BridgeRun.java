package com.anash.bridge.runner;

import com.anash.bridge.abstraction.BaseList;
import com.anash.bridge.abstraction.NumberedList;
import com.anash.bridge.implementor.OrderedListImpl;
import com.anash.bridge.abstraction.OrnamentedList;

public class BridgeRun {
    public static void main(String[] args) {
        OrderedListImpl implementation = new OrderedListImpl();

        BaseList baseList = new BaseList();
        baseList.setImplementor(implementation);

        baseList.add("One");
        baseList.add("Two");
        baseList.add("Three");
        baseList.add("Four");

        OrnamentedList ornamentedList = new OrnamentedList();
        ornamentedList.setImplementor(implementation);
        ornamentedList.setItemType('*');

        NumberedList numberedList = new NumberedList();
        numberedList.setImplementor(implementation);

        System.out.println("=== First (base) list ===");
        for (int i = 0; i < baseList.count(); i++) {
            System.out.println("\t" + baseList.get(i));
        }

        System.out.println("=== Second (ornamented) list ===");
        for (int i = 0; i < ornamentedList.count(); i++) {
            System.out.println("\t" + ornamentedList.get(i));
        }

        System.out.println("=== Third (numbered) list ===");
        for (int i = 0; i < numberedList.count(); i++) {
            System.out.println("\t" + numberedList.get(i));
        }
    }
}
