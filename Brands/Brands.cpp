#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
using namespace eosio;
using namespace std;
class Brands : public eosio::contract
{
    public:
        using contract::contract;
        /// @abi table
        struct brands
        {
            uint64_t id;
            account_name first;
            account_name to;
            account_name from;
            string brands_name;
            string product_name;
            string brands_num;
            string type;
            string reg_dttm;
            string mf_dttm;
            string tx_dttm;
            uint64_t primary_key() const {return id;}
            EOSLIB_SERIALIZE(brands,(id)(first)(to)(from)(brands_name)(product_name)(brands_num)(type)(reg_dttm)(mf_dttm)(tx_dttm))
        };
        typedef multi_index<N(brands),brands> _brands;
        /// @abi action
        void create(uint64_t id, account_name first, account_name to, account_name from, string brands_name, string product_name,
                     string brands_num, string type, string reg_dttm, string mf_dttm, string tx_dttm)
        {
             _brands tables(_self,_self);

            auto iter=tables.find(id);
            if(iter==tables.end())
            {
                tables.emplace(_self,[&](auto& brands)
                {
                    brands.id = id;
                    brands.first = first;
                    brands.to = to;
                    brands.from = from;
                    brands.brands_name = brands_name;
                    brands.product_name = product_name;
                    brands.brands_num = brands_num;
                    brands.type = type;
                    brands.reg_dttm = reg_dttm;
                    brands.mf_dttm = mf_dttm;
                    brands.tx_dttm = tx_dttm;
                });
            }
            else
            {
                uint64_t getuser;
                getuser=iter->to;
            }
        }
        //delete
        void del(uint64_t id, string _brands_num)
        {
            _brands tables(_self,_self);
            auto iter=tables.find(id);
            if(iter!=tables.end())
            {
                tables.erase(iter);
            }
        }
        //edit (product edit)
        void edit(uint64_t id, string _product_name, string _brands_num, string _type, string _reg_dttm, string _mf_dttm)
        {
             _brands tables(_self,_self);
            auto iter=tables.find(id);
            if(iter!=tables.end())
            {
                tables.modify(iter,_self,[&](auto& edit_table)
                {
                  edit_table.brands_num = _brands_num;
                  edit_table.product_name = _product_name;
                  edit_table.reg_dttm = _reg_dttm;
                  edit_table.mf_dttm = _mf_dttm;
                  edit_table.type = _type;

                });
            }
        }
        void auth(uint64_t id, account_name first, account_name to, account_name from, string brands_name, string product_name,
                     string brands_num, string type, string reg_dttm, string mf_dttm, string tx_dttm)
        {
            _brands tables(_self,_self);
           auto iter=tables.find(id);
           if(iter!=tables.end())
           {
               tables.modify(iter,_self,[&](auto& edit_table)
               {
                 edit_table.id = id;
                 edit_table.first = first;
                 edit_table.to = to;
                 edit_table.from = from;
                 edit_table.brands_name = brands_name;
                 edit_table.product_name = product_name;
                 edit_table.brands_num = brands_num;
                 edit_table.type = type;
                 edit_table.reg_dttm = reg_dttm;
                 edit_table.mf_dttm = mf_dttm;
                 edit_table.tx_dttm = tx_dttm;
               });
           }
        }

};
EOSIO_ABI(Brands,(create)(del)(edit)(auth))
