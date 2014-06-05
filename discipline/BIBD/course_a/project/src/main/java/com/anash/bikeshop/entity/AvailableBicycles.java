package com.anash.bikeshop.entity;

import org.hibernate.annotations.GenericGenerator;

import javax.persistence.*;
import java.io.Serializable;

@Entity
@Table(name = "available_bicycles")
public class AvailableBicycles implements Serializable {

    @Id
    @GeneratedValue(generator = "increment")
    @GenericGenerator(name = "increment", strategy = "increment")
    @Column(name = "id", length = 6, nullable = false)
    private long id;

    @OneToOne(cascade = CascadeType.ALL)
    @JoinColumn(name = "bicycle_id", nullable = false)
    private Bicycles bicycle;

    @Column(name = "products_count")
    private Integer count;

    @Column(name = "availability")
    private Boolean availability;
}
