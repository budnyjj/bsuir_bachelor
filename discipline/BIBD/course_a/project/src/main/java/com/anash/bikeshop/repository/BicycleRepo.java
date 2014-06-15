package com.anash.bikeshop.repository;

import com.anash.bikeshop.entity.Bicycle;
import org.springframework.data.jpa.repository.JpaRepository;

public interface BicycleRepo
        extends JpaRepository<Bicycle, Integer> {
}
