-- usage example:
-- call update_row(2,'cheese',300,15,'2014-05-01');

delimiter endproc
create procedure update_row(
    IN _id int,
    _title varchar(25),
    _price int,
    _count int,
    _deliveryDate Date)
begin
    update warehouse
        set title = _title,
            price = _price,
            count = _count,
            deliveryDate = _deliveryDate
        where id = _id;
end;
endproc
delimiter ;
