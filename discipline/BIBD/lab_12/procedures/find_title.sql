-- usage example
-- call tax('m', @title);
-- select @title;

delimiter endproc
create procedure find_title(
    IN _title_part varchar(25),
    OUT _title varchar(25))
begin
    select group_concat(title separator '|\n|')
        into _title
        from warehouse
        where title like concat('%', _title_part, '%'); 
end;
endproc
delimiter ;