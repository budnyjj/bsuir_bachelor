-- usage example
-- call count_of_repeating_elements(@count);
-- select @count;

delimiter endproc
create procedure count_of_repeating_elements(
    OUT _count int)
begin
    declare all_titles_count int;
    declare unique_titles_count int;

    select count(title) from warehouse 
        into all_titles_count;

    select count(title) from 
        ((select title from warehouse group by title) as temp)
        into unique_titles_count;

    set _count = all_titles_count - unique_titles_count;
end;
endproc
delimiter ;