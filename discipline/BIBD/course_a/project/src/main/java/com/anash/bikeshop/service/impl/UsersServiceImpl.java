package com.anash.bikeshop.service.impl;

import com.anash.bikeshop.entity.Users;
import com.anash.bikeshop.repository.UsersRepo;
import com.anash.bikeshop.service.UsersService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class UsersServiceImpl implements UsersService {

    @Autowired
    private UsersRepo usersRepo;

    @Override
    public void create(Users user) {      // Create
        Users createdUser = user;
        usersRepo.saveAndFlush(createdUser);
    }

    @Override
    public Users getById(long id) {     // Read
        return usersRepo.findOne(id);
    }
    @Override
    public void update(Users user) {    // Update
        usersRepo.saveAndFlush(user);
    }

    @Override
    public void delete(Users user) {    // Delete
        usersRepo.delete(user);
    }
}
