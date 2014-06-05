package com.anash.bikeshop.repository;

import com.anash.bikeshop.entity.AvailableBicycles;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface AvailableBicyclesRepo
        extends JpaRepository<AvailableBicycles, Long> {

}
