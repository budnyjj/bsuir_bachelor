package com.anash.bikeshop.repository;

import com.anash.bikeshop.entity.User;
import org.springframework.data.jpa.repository.JpaRepository;

public interface UserRepo
        extends JpaRepository<User, Integer> {
}
