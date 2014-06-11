package com.anash.bikeshop.service.impl;

import com.anash.bikeshop.entity.Bicycles;
import com.anash.bikeshop.repository.BicyclesRepo;
import com.anash.bikeshop.service.BicyclesService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class BicyclesServiceImpl implements BicyclesService {

    @Autowired
    private BicyclesRepo bicyclesRepo;

    @Override
    public void create(Bicycles bicycles) {
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

    @Override
    public List<Bicycles> getAll() {
        return bicyclesRepo.findAll();
    }
}
