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
    public User save(User user) {
        User createdUser;
        createdUser = userRepo.saveAndFlush(user);
        return createdUser;
    }

    /*
    @Override
    public void update(User user) {
        userRepo.saveAndFlush(user);
    }
    */

    @Override
    public void delete(Integer id) {
        userRepo.delete(id);
    }

    @Override
    public User findById(Integer id) {
        return userRepo.findOne(id);
    }

    @Override
    public List<User> getAll() {
        return userRepo.findAll();
    }
}
