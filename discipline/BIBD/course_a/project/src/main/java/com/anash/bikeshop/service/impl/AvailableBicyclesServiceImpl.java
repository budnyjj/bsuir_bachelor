package com.anash.bikeshop.service.impl;

import com.anash.bikeshop.entity.AvailableBicycles;
import com.anash.bikeshop.entity.Bicycles;
import com.anash.bikeshop.repository.AvailableBicyclesRepo;
import com.anash.bikeshop.service.AvailableBicyclesService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

@Service
public class AvailableBicyclesServiceImpl implements AvailableBicyclesService {

    @Autowired
    private AvailableBicyclesRepo availableBicyclesRepo;

    @Override
    public void create(AvailableBicycles entity) {
        availableBicyclesRepo.saveAndFlush(entity);
    }

    @Override
    public void update(AvailableBicycles entity) {
        availableBicyclesRepo.saveAndFlush(entity);
    }

    @Override
    public void delete(AvailableBicycles entity) {
        availableBicyclesRepo.delete(entity);
    }

    @Override
    public AvailableBicycles getById(long id) {
        return availableBicyclesRepo.findOne(id);
    }

    @Override
    public List<AvailableBicycles> getAll() {
        return availableBicyclesRepo.findAll();
    }

    @Override
    public List<Bicycles> getAvailableBicyclesList() {

        List<AvailableBicycles> availableBicycles = availableBicyclesRepo.findAll();
        ArrayList<Bicycles> bicycles = new ArrayList<>();

        for (AvailableBicycles availableBicycle : availableBicycles) {
            bicycles.add(availableBicycle.getBicycle());
        }
        return bicycles;
    }
}
