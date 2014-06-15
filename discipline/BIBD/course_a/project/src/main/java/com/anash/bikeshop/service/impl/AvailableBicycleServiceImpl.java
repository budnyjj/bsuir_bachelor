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
    public void create(AvailableBicycle availableBicycle) {
        AvailableBicycle createdAvailableBicycle = availableBicycle;
        availableBicycleRepo.saveAndFlush(createdAvailableBicycle);
    }

    @Override
    public void update(AvailableBicycle entity) {
        availableBicycleRepo.saveAndFlush(entity);
    }

    @Override
    public void delete(AvailableBicycle entity) {
        availableBicycleRepo.delete(entity);
    }

    @Override
    public AvailableBicycle getById(Integer id) {
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
}
