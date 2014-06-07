package com.anash.bikeshop.service.impl;

import com.anash.bikeshop.entity.AvailableBicycles;
import com.anash.bikeshop.repository.AvailableBicyclesRepo;
import com.anash.bikeshop.service.AvailableBicyclesService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

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
        return null;
    }
}
