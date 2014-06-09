package com.anash.bikeshop.service;

import com.anash.bikeshop.entity.AvailableBicycles;
import com.anash.bikeshop.entity.Bicycles;

import java.util.List;

public interface AvailableBicyclesService extends Service<AvailableBicycles> {

    List<Bicycles> getAvailableBicyclesList();

}
