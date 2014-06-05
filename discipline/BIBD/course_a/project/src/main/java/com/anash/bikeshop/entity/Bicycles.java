package com.anash.bikeshop.entity;

import com.anash.bikeshop.entity.enums.BicycleSize;
import com.anash.bikeshop.entity.enums.FrameMaterial;
import org.hibernate.annotations.GenericGenerator;
import org.hibernate.validator.constraints.Range;

import javax.persistence.*;
import java.io.Serializable;
import java.time.Year;

@Entity
@Table(name = "bicycles")
public class Bicycles implements Serializable {

    @Id
    @GeneratedValue(generator = "increment")
    @GenericGenerator(name = "increment", strategy = "increment")
    @Column(name = "id", length = 6, nullable = false)
    private long id;

    @Column(name = "product_name", nullable = false)
    private String productName;

    @Column(name = "manufacturer", nullable = false)
    private String manufacturer;

    @Column(name = "type")
    private String type;

    @Range(min = 1900, max = 2500)
    @Column(name = "year")
    private Year year;

    @Column(name = "color")
    private String color;

    @Enumerated(EnumType.STRING)
    @Column(name = "bicycle_size", nullable = false)
    private BicycleSize size;

    @Range(min = 1, max = 50)
    @Column(name = "rates_number")
    private Byte ratesNumber;

    @Column(name = "weight")
    private Double weight;

    @Column(name = "brakes")
    private String brakes;

    @Range(min = 1, max = 50)
    @Column(name = "wheels_diameter")
    private Byte wheelsDiameter;

    @Enumerated(EnumType.STRING)
    @Column(name = "frame_materials")
    private FrameMaterial frameMaterial;

    @Column(name = "fork")
    private String fork;

    @Column(name = "lockout")
    private Boolean lockout;

    @Range(max = 300)
    @Column(name = "fork_move")
    private Integer forkMove;

    @Column(name = "front_derailer")
    private String frontDerailer;

    @Column(name = "rear_derailer")
    private String rearDerailer;

    @Column(name = "crackset")
    private String crackset;

    @Column(name = "cassette")
    private String cassette;

    @Column(name = "saddle")
    private String saddle;

    @Column(name = "shifters")
    private String shifters;

    @Column(name = "chain")
    private String chain;

    @Column(name = "handlebar")
    private String handlebar;

    @Column(name = "pedals")
    private String pedals;

    @Column(name = "sprockets")
    private String sprockets;

    @Column(name = "tires")
    private String tires;

    @Column(name = "guarantee")
    private String guarantee;

    @Column(name = "photo_path")
    private String photoPath;

    @Column(name = "price")
    private Double price;
}
