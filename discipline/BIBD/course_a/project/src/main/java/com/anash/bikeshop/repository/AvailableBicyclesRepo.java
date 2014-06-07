package com.anash.bikeshop.repository;

import com.anash.bikeshop.entity.AvailableBicycles;
import org.springframework.data.jpa.repository.JpaRepository;

public interface AvailableBicyclesRepo
        extends JpaRepository<AvailableBicycles, Long> {

}
