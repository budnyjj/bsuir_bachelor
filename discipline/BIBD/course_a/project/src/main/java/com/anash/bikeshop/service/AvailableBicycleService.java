package com.anash.bikeshop.service;

import com.anash.bikeshop.entity.AvailableBicycle;
import com.anash.bikeshop.entity.Bicycle;

import java.util.List;

public interface AvailableBicycleService extends Service<AvailableBicycle> {

    List<Bicycle> getAvailableBicyclesList();

}
