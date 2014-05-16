-- usage example
-- call tax(12, @tax);
-- select @tax;

delimiter endproc
create procedure tax(
    IN percent int, 
    OUT result float)
begin
    declare sum_count int;
    declare sum_price int;
    select sum(price) from warehouse into sum_price;
    select sum(count) from warehouse into sum_count;
    set result = sum_count * sum_count * percent / 100;
end;
endproc
delimiter ;