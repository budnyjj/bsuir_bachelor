-- usage example:
-- call insert_row('cheese',30000,15,'2014-05-01');

delimiter endproc
create procedure insert_row(
    IN _title varchar(25),
    _price int,
    _count int,
    _deliveryDate Date)
begin
    declare max_id int;
    select max(id) from warehouse into max_id;

    insert into warehouse(id, title, price, count, deliveryDate)
        values (max_id+1, _title, _price, _count, _deliveryDate);

end;
endproc
delimiter ;