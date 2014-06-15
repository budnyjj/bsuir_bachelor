package com.anash.bikeshop.service.impl;

import com.anash.bikeshop.entity.Bicycle;
import com.anash.bikeshop.repository.BicycleRepo;
import com.anash.bikeshop.service.BicycleService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class BicycleServiceImpl implements BicycleService {

    @Autowired
    private BicycleRepo bicycleRepo;

    @Override
    public void create(Bicycle bicycle) {
        Bicycle createdBicycle = bicycle;
        bicycleRepo.saveAndFlush(createdBicycle);
    }

    @Override
    public void update(Bicycle bicycle) {
        bicycleRepo.saveAndFlush(bicycle);
    }

    @Override
    public void delete(Bicycle bicycle) {
        bicycleRepo.delete(bicycle);
    }

    @Override
    public Bicycle getById(Integer id) {
        return bicycleRepo.findOne(id);
    }

    @Override
    public List<Bicycle> getAll() {
        return bicycleRepo.findAll();
    }
}
