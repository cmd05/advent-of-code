use std::fs;

fn main() {
    let data = fs::read_to_string("./day1p1.txt").expect("Unable to read file");
    let lines = data.split("\n");
    let mut v1: Vec<i32> = vec![];
    let mut v2: Vec<i32> = vec![];

    for (_pos, line) in lines.enumerate() {
        let nums = line.trim_end().split("   ").collect::<Vec<_>>();
        
        if nums.len() == 1 { // skip last line
            continue;
        }
        
        v1.push(nums[0].parse().unwrap());
        v2.push(nums[1].parse().unwrap());
    }

    v1.sort();
    v2.sort();

    let mut tdist = 0;
    
    for i in 0..v1.len() {
        tdist += i32::abs(v1[i] - v2[i]);
    }

    print!("{}", tdist);
}