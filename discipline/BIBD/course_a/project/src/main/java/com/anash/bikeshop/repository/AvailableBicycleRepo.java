package com.anash.bikeshop.repository;

import com.anash.bikeshop.entity.AvailableBicycle;
import org.springframework.data.jpa.repository.JpaRepository;

public interface AvailableBicycleRepo
        extends JpaRepository<AvailableBicycle, Integer> {

}
