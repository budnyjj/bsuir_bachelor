package com.anash.bikeshop.service.impl;

import com.anash.bikeshop.entity.AvailableBicycle;
import com.anash.bikeshop.entity.Bicycle;
import com.anash.bikeshop.repository.AvailableBicycleRepo;
import com.anash.bikeshop.service.AvailableBicycleService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

@Service
public class AvailableBicycleServiceImpl implements AvailableBicycleService {

    @Autowired
    private AvailableBicycleRepo availableBicycleRepo;

    @Override
    public AvailableBicycle save(AvailableBicycle availableBicycle) {
        AvailableBicycle createdAvailableBicycle;
        createdAvailableBicycle = availableBicycleRepo.saveAndFlush(availableBicycle);
        return createdAvailableBicycle;
    }
/*
    @Override
    public void update(AvailableBicycle entity) {
        availableBicycleRepo.saveAndFlush(entity);
    }
*/
    @Override
    public void delete(Integer id) {
        availableBicycleRepo.delete(id);
    }

    @Override
    public AvailableBicycle findById(Integer id) {
        return availableBicycleRepo.findOne(id);
    }

    @Override
    public List<AvailableBicycle> getAll() {
        return availableBicycleRepo.findAll();
    }

    @Override
    public List<Bicycle> getAvailableBicyclesList() {

        List<AvailableBicycle> availableBicycles = availableBicycleRepo.findAll();
        ArrayList<Bicycle> bicycles = new ArrayList<>();

        for (AvailableBicycle availableBicycle : availableBicycles)
            bicycles.add(availableBicycle.getBicycle());

        return bicycles;
    }

    @Override
    public AvailableBicycle findAvailableBicycleByBicycleId(Integer id) {
        List<AvailableBicycle> availableBicycles = getAll();

        AvailableBicycle availableBicycle = null;
        for (AvailableBicycle ab : availableBicycles) {
            if (ab.getBicycle().getId() == id) {
                availableBicycle = ab;
            }
        }

        return availableBicycle;
    }
}
