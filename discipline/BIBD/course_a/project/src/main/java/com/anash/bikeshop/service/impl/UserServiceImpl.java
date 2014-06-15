package com.anash.bikeshop.service.impl;

import com.anash.bikeshop.entity.User;
import com.anash.bikeshop.repository.UserRepo;
import com.anash.bikeshop.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class UserServiceImpl implements UserService {

    @Autowired
    private UserRepo userRepo;

    @Override
    public void create(User user) {
        User createdUser = user;
        userRepo.saveAndFlush(createdUser);
    }

    @Override
    public void update(User user) {
        userRepo.saveAndFlush(user);
    }

    @Override
    public void delete(User user) {
        userRepo.delete(user);
    }

    @Override
    public User getById(Integer id) {
        return userRepo.findOne(id);
    }

    @Override
    public List<User> getAll() {
        return userRepo.findAll();
    }
}
