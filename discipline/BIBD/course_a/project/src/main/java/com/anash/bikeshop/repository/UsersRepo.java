package com.anash.bikeshop.repository;

import com.anash.bikeshop.entity.Users;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface UsersRepo
        extends JpaRepository<Users, Long> {
}
