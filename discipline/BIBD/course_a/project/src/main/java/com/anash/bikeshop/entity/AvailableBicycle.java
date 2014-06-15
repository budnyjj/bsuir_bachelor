package com.anash.bikeshop.entity;

import javax.persistence.*;
import javax.validation.constraints.NotNull;
import java.io.Serializable;

@Entity
@Table(name = "available_bicycles")
public class AvailableBicycle implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private int id;

    @NotNull
    @OneToOne(cascade = CascadeType.ALL)
    @JoinColumn(name = "bicycle_id", nullable = false, unique = true)
    private Bicycle bicycle;

    @Column(name = "bicycles_count")
    private Integer count;

    @Column
    private Boolean availability;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public Bicycle getBicycle() {
        return bicycle;
    }

    public void setBicycle(Bicycle bicycle) {
        this.bicycle = bicycle;
    }

    public Integer getCount() {
        return count;
    }

    public void setCount(Integer count) {
        this.count = count;
        this.availability = count > 0;

    }

    public Boolean getAvailability() {
        return availability;
    }

    public void setAvailability(Boolean availability) {
        this.availability = availability;
    }
}
