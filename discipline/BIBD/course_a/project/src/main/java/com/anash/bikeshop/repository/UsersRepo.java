package com.anash.bikeshop.repository;

import com.anash.bikeshop.entity.Users;
import org.springframework.data.jpa.repository.JpaRepository;

public interface UsersRepo
        extends JpaRepository<Users, Long> {
}
