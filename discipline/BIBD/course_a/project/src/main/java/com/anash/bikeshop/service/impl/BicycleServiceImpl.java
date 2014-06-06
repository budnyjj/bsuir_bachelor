package com.anash.bikeshop.service.impl;

import com.anash.bikeshop.entity.Bicycles;
import com.anash.bikeshop.repository.BicyclesRepo;
import com.anash.bikeshop.service.BicycleService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class BicycleServiceImpl implements BicycleService {

    @Autowired
    private BicyclesRepo bicyclesRepo;

    @Override
    public void save(Bicycles bicycles) {
        bicyclesRepo.saveAndFlush(bicycles);
    }

    @Override
    public void update(Bicycles bicycles) {
        bicyclesRepo.saveAndFlush(bicycles);
    }

    @Override
    public void delete(Bicycles bicycles) {
        bicyclesRepo.delete(bicycles);
    }

    @Override
    public Bicycles getById(long id) {
        return bicyclesRepo.findOne(id);
    }
}
